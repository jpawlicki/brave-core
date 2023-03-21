/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <string>
#include <utility>

#include "base/test/task_environment.h"
#include "brave/components/brave_rewards/core/endpoint/gemini/post_balance/post_balance_gemini.h"
#include "brave/components/brave_rewards/core/ledger.h"
#include "brave/components/brave_rewards/core/ledger_client_mock.h"
#include "brave/components/brave_rewards/core/ledger_impl_mock.h"
#include "net/http/http_status_code.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- brave_unit_tests --filter=GeminiPostBalanceTest.*

using ::testing::_;

namespace ledger {
namespace endpoint {
namespace gemini {

class GeminiPostBalanceTest : public testing::Test {
 protected:
  base::test::TaskEnvironment task_environment_;
  MockLedgerImpl mock_ledger_impl_;
  PostBalance balance_{&mock_ledger_impl_};
};

TEST_F(GeminiPostBalanceTest, ServerOK) {
  ON_CALL(*mock_ledger_impl_.mock_client(), LoadURL(_, _))
      .WillByDefault(
          [](mojom::UrlRequestPtr request, LoadURLCallback callback) {
            auto response = mojom::UrlResponse::New();
            response->status_code = net::HTTP_OK;
            response->url = request->url;
            response->body = R"([
              {
                  "type": "exchange",
                  "currency": "BTC",
                  "amount": "1000.01195318",
                  "available": "1000.01195318",
                  "availableForWithdrawal": "1000.01195318"
              },
              {
                  "type": "exchange",
                  "currency": "ETH",
                  "amount": "20000",
                  "available": "20000",
                  "availableForWithdrawal": "20000"
              },
              {
                  "type": "exchange",
                  "currency": "BAT",
                  "amount": "5000",
                  "available": "5000",
                  "availableForWithdrawal": "5000"
              },
              {
                  "type": "exchange",
                  "currency": "USD",
                  "amount": "93687.50",
                  "available": "93677.40",
                  "availableForWithdrawal": "93677.40"
              }
            ])";
            std::move(callback).Run(std::move(response));
          });

  balance_.Request(
      "4c2b665ca060d912fec5c735c734859a06118cc8",
      base::BindOnce([](const mojom::Result result, const double available) {
        EXPECT_EQ(result, mojom::Result::LEDGER_OK);
        EXPECT_EQ(available, 5000.0);
      }));
}

TEST_F(GeminiPostBalanceTest, ServerError401) {
  ON_CALL(*mock_ledger_impl_.mock_client(), LoadURL(_, _))
      .WillByDefault(
          [](mojom::UrlRequestPtr request, LoadURLCallback callback) {
            auto response = mojom::UrlResponse::New();
            response->status_code = net::HTTP_UNAUTHORIZED;
            response->url = request->url;
            response->body = "";
            std::move(callback).Run(std::move(response));
          });

  balance_.Request(
      "4c2b665ca060d912fec5c735c734859a06118cc8",
      base::BindOnce([](const mojom::Result result, const double available) {
        EXPECT_EQ(result, mojom::Result::EXPIRED_TOKEN);
        EXPECT_EQ(available, 0.0);
      }));
}

TEST_F(GeminiPostBalanceTest, ServerError403) {
  ON_CALL(*mock_ledger_impl_.mock_client(), LoadURL(_, _))
      .WillByDefault(
          [](mojom::UrlRequestPtr request, LoadURLCallback callback) {
            auto response = mojom::UrlResponse::New();
            response->status_code = net::HTTP_FORBIDDEN;
            response->url = request->url;
            response->body = "";
            std::move(callback).Run(std::move(response));
          });

  balance_.Request(
      "4c2b665ca060d912fec5c735c734859a06118cc8",
      base::BindOnce([](const mojom::Result result, const double available) {
        EXPECT_EQ(result, mojom::Result::EXPIRED_TOKEN);
        EXPECT_EQ(available, 0.0);
      }));
}

TEST_F(GeminiPostBalanceTest, ServerError404) {
  ON_CALL(*mock_ledger_impl_.mock_client(), LoadURL(_, _))
      .WillByDefault(
          [](mojom::UrlRequestPtr request, LoadURLCallback callback) {
            auto response = mojom::UrlResponse::New();
            response->status_code = net::HTTP_NOT_FOUND;
            response->url = request->url;
            response->body = "";
            std::move(callback).Run(std::move(response));
          });

  balance_.Request(
      "4c2b665ca060d912fec5c735c734859a06118cc8",
      base::BindOnce([](const mojom::Result result, const double available) {
        EXPECT_EQ(result, mojom::Result::NOT_FOUND);
        EXPECT_EQ(available, 0.0);
      }));
}

TEST_F(GeminiPostBalanceTest, ServerErrorRandom) {
  ON_CALL(*mock_ledger_impl_.mock_client(), LoadURL(_, _))
      .WillByDefault(
          [](mojom::UrlRequestPtr request, LoadURLCallback callback) {
            auto response = mojom::UrlResponse::New();
            response->status_code = 418;
            response->url = request->url;
            response->body = "";
            std::move(callback).Run(std::move(response));
          });

  balance_.Request(
      "4c2b665ca060d912fec5c735c734859a06118cc8",
      base::BindOnce([](const mojom::Result result, const double available) {
        EXPECT_EQ(result, mojom::Result::LEDGER_ERROR);
        EXPECT_EQ(available, 0.0);
      }));
}

}  // namespace gemini
}  // namespace endpoint
}  // namespace ledger
