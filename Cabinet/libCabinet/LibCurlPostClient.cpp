#include <curl/curl.h>
#include <string>
#include "LibCurlPostClient.h"


size_t WriteData(char *receivedBuffer, size_t receivedSize,
    size_t newMemoryBytes, std::string *stringPointer)
{
	stringPointer->append(receivedBuffer, newMemoryBytes);
	return receivedSize * newMemoryBytes;
}

bool LibCurlPostClient::SendPostMsg(std::string URL, std::string data)
{
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl)
    {

        std::string receivedData;

        /* First set the URL that is about to receive our POST. This URL can
        just as well be a https:// URL if that is what should receive the
        data. */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &receivedData);
        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
        {
            /* error has occured - cleanup*/
            curl_easy_cleanup(curl);
            return false;
        }

        /* always cleanup */
        curl_easy_cleanup(curl);

        return true;
    }
    else
    {
        /* curl handle not created */
        return false;
    }

}
