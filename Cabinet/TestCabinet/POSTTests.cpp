#include <gtest/gtest.h>
#include "HTTPPostClientSpy.h"
#include "LibCurlPostClient.h"
#include "Postman.h"

#include "TestFunctions.hpp"

using namespace testing;

/*********************************
 ****Actual Libcurl Post**********/
/*TEST(LibCurlPOSTTests, Curl_send_attempt_to_HTTPBinOrg_returns_true)
{
    LibCurlPostClient testClient;
    EXPECT_EQ(true, testClient.sendPostMsg("http://httpbin.org/post", "TEST"));
}

TEST(LibCurlPOSTTests, Curl_send_attempt_to_GibberishInvalid_returns_false)
{
    LibCurlPostClient testClient;
    EXPECT_EQ(false, testClient.sendPostMsg("http://gibberish.invalid", "TEST"));
}*/

/*********************************
 *******Postman Tests*************/

TEST(PostmanTests, Postman_returns_false_when_client_fails)
{
    HTTPPostClientSpy testClient;
    testClient.sendPostMsgResult = false;
    Postman pat("http://gibberish.invalid", &testClient);
    EXPECT_EQ(false, pat.sendEventNotification("AAE114", false, false));
}

TEST(PostmanTests, Postman_returns_true_when_client_succeeds)
{
    HTTPPostClientSpy testClient;
    testClient.sendPostMsgResult = true;
    Postman pat("http://gibberish.invalid", &testClient);
    EXPECT_EQ(true, pat.sendEventNotification("AAE114", false, false));
}

TEST(PostmanTests, Postman_sends_to_URL_given)
{
    HTTPPostClientSpy testClient;
    testClient.sendPostMsgResult = true;
    Postman pat("http://gibberish.invalid", &testClient);
    pat.sendEventNotification("AAE114", false, false);
    EXPECT_EQ("http://gibberish.invalid", testClient.lastPOSTURL);
}

TEST(PostmanTests, Postman_sends_data_formatted_correctly)
{

    HTTPPostClientSpy testClient;
    testClient.sendPostMsgResult = true;
    Postman pat("http://gibberish.invalid", &testClient);
    pat.sendEventNotification("AA123", false, false);
    ASSERT_TRUE(IsSubstringPresentInOutputString("  \"cabinet_id\" : \"AA123\", \n", testClient.lastPOSTData));


}
