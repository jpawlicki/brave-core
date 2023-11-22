/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "base/strings/string_split.h"
#include "brave/components/brave_rewards/core/database/database.h"
#include "brave/components/brave_rewards/core/report/report.h"
#include "brave/components/brave_rewards/core/rewards_engine_impl.h"

using std::placeholders::_1;

namespace brave_rewards::internal {
namespace report {

Report::Report(RewardsEngineImpl& engine) : engine_(engine) {}

Report::~Report() = default;

void Report::GetMonthly(const mojom::ActivityMonth month,
                        const int year,
                        GetMonthlyReportCallback callback) {
  auto balance_callback =
      base::BindOnce(&Report::OnBalance, base::Unretained(this), month, year,
                     std::move(callback));

  engine_->database()->GetBalanceReportInfo(month, year,
                                            std::move(balance_callback));
}

void Report::OnBalance(const mojom::ActivityMonth month,
                       const uint32_t year,
                       GetMonthlyReportCallback callback,
                       const mojom::Result result,
                       mojom::BalanceReportInfoPtr balance_report) {
  if (result != mojom::Result::OK || !balance_report) {
    BLOG(0, "Could not get balance report");
    callback(result, nullptr);
    return;
  }

  auto monthly_report = mojom::MonthlyReportInfo::New();
  monthly_report->balance = std::move(balance_report);

  auto transaction_callback = std::bind(
      &Report::OnTransactions, this, _1, month, year,
      std::make_shared<mojom::MonthlyReportInfoPtr>(std::move(monthly_report)),
      callback);

  engine_->database()->GetTransactionReport(month, year, transaction_callback);
}

void Report::OnTransactions(
    std::vector<mojom::TransactionReportInfoPtr> transaction_report,
    const mojom::ActivityMonth month,
    const uint32_t year,
    std::shared_ptr<mojom::MonthlyReportInfoPtr> shared_report,
    GetMonthlyReportCallback callback) {
  if (!shared_report) {
    BLOG(0, "Could not parse monthly report");
    callback(mojom::Result::FAILED, nullptr);
    return;
  }

  (*shared_report)->transactions = std::move(transaction_report);

  engine_->database()->GetContributionReport(
      month, year,
      base::BindOnce(&Report::OnContributions, base::Unretained(this),
                     shared_report, std::move(callback)));
}

void Report::OnContributions(
    std::shared_ptr<mojom::MonthlyReportInfoPtr> shared_report,
    GetMonthlyReportCallback callback,
    std::vector<mojom::ContributionReportInfoPtr> contribution_report) {
  if (!shared_report) {
    BLOG(0, "Could not parse monthly report");
    callback(mojom::Result::FAILED, nullptr);
    return;
  }

  (*shared_report)->contributions = std::move(contribution_report);

  callback(mojom::Result::OK, std::move(*shared_report));
}

// This will be removed when we move reports in database and just order in db
bool CompareReportIds(const std::string& id_1, const std::string& id_2) {
  auto id_1_parts = base::SplitString(id_1, "_", base::TRIM_WHITESPACE,
                                      base::SPLIT_WANT_NONEMPTY);

  auto id_2_parts = base::SplitString(id_2, "_", base::TRIM_WHITESPACE,
                                      base::SPLIT_WANT_NONEMPTY);

  DCHECK(id_1_parts.size() == 2 && id_2_parts.size() == 2);

  const int id_1_year = std::stoi(id_1_parts[0]);
  const int id_2_year = std::stoi(id_2_parts[0]);
  const int id_1_month = std::stoi(id_1_parts[1]);
  const int id_2_month = std::stoi(id_2_parts[1]);

  if (id_1_year == id_2_year) {
    return id_1_month > id_2_month;
  }

  return id_1_year > id_2_year;
}

void Report::GetAllMonthlyIds(GetAllMonthlyReportIdsCallback callback) {
  engine_->database()->GetAllBalanceReports(
      base::BindOnce(&Report::OnGetAllBalanceReports, base::Unretained(this),
                     std::move(callback)));
}

void Report::OnGetAllBalanceReports(
    GetAllMonthlyReportIdsCallback callback,
    std::vector<mojom::BalanceReportInfoPtr> reports) {
  if (reports.empty()) {
    std::move(callback).Run({});
    return;
  }

  std::vector<std::string> ids;

  for (const auto& report : reports) {
    ids.push_back(report->id);
  }

  std::sort(ids.begin(), ids.end(), CompareReportIds);

  std::move(callback).Run(ids);
}

}  // namespace report
}  // namespace brave_rewards::internal
