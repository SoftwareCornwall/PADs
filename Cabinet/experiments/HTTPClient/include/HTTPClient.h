#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H


class HTTPClient
{
    public:
        HTTPClient(std::string ServerURL, std::string POSTdata);
        virtual ~HTTPClient();
    protected:
    private:
};

#endif // HTTPCLIENT_H
