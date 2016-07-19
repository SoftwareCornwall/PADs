#include <gtest/gtest.h>
#include "HTTPPostClientSpy.h"
#include "LibCurlPostClient.h"
#include "Postman.h"

using namespace testing;

TEST(PostmanTests, Postman_returns_false_when_client_fails)
{
    HTTPPostClientSpy testClient;
    testClient.sendPostMsgResult = false;
    Postman pat("http://gibberish.invalid", &testClient);
    EXPECT_EQ(false, pat.SendEventNotification("AAE114", "Open", "Available"));
}

TEST(PostmanTests, Postman_returns_true_when_client_succeeds)
{
    HTTPPostClientSpy testClient;
    testClient.sendPostMsgResult = true;
    Postman pat("http://gibberish.invalid", &testClient);
    EXPECT_EQ(true, pat.SendEventNotification("AAE114", "Open", "Available"));
}

TEST(PostmanTests, Postman_sends_to_URL_given)
{
    HTTPPostClientSpy testClient;
    testClient.sendPostMsgResult = true;
    Postman pat("http://gibberish.invalid", &testClient);
    pat.SendEventNotification("AAE114", "Open", "Available");
    EXPECT_EQ("http://gibberish.invalid", testClient.lastPOSTURL);
}

TEST(PostmanTests, Postman_sends_data_formatted_correctly)
{

    std::string boxPOSTData = "{\n"
    "  \"cabinet_id\" : \"AAE114\", \n"
    "  \"door_status\" : \"Open\", \n"
    "  \"defib_status\" : \"Available\" \n"
    "}";
    HTTPPostClientSpy testClient;
    testClient.sendPostMsgResult = true;
    Postman pat("http://gibberish.invalid", &testClient);
    pat.SendEventNotification("AAE114", "Open", "Available");
    EXPECT_EQ(boxPOSTData, testClient.lastPOSTData);
}
