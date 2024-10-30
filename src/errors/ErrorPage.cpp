#include "../../header/ErrorPage.hpp"

ErrorPage::ErrorPage()
{
    initErrMsg();
}

void ErrorPage::initErrMsg()
{
    errorPages[400] = "<html><body><h1>400 Bad Request</h1><p>Your request could not be understood by the server.</p></body></html>";
    errorPages[401] = "<html><body><h1>401 Unauthorized</h1><p>You are not authorized to access this resource.</p></body></html>";
    errorPages[402] = "<html><body><h1>402 Payment Required</h1><p>Payment is required to access this resource.</p></body></html>";
    errorPages[403] = "<html><body><h1>403 Forbidden</h1><p>You do not have permission to access this resource.</p></body></html>";
    errorPages[404] = "<html><body><h1>404 Not Found </h1><p>The requested resource was not found.</p></body></html>";
    errorPages[405] = "<html><body><h1>405 Method Not Allowed</h1><p>The requested method is not allowed for this resource.</p></body></html>";
    errorPages[406] = "<html><body><h1>406 Not Acceptable</h1><p>The requested resource is not available in a format acceptable to your browser.</p></body></html>";
    errorPages[407] = "<html><body><h1>407 Proxy Authentication Required</h1><p>Authentication with a proxy server is required.</p></body></html>";
    errorPages[408] = "<html><body><h1>408 Request Timeout</h1><p>The server timed out waiting for your request.</p></body></html>";
    errorPages[409] = "<html><body><h1>409 Conflict</h1><p>There was a conflict with the request.</p></body></html>";
    errorPages[410] = "<html><body><h1>410 Gone</h1><p>The requested resource is no longer available.</p></body></html>";
    errorPages[411] = "<html><body><h1>411 Length Required</h1><p>A valid Content-Length header is required.</p></body></html>";
    errorPages[412] = "<html><body><h1>412 Precondition Failed</h1><p>A precondition for this request was not met.</p></body></html>";
    errorPages[413] = "<html><body><h1>413 Payload Too Large</h1><p>The request payload is too large.</p></body></html>";
    errorPages[414] = "<html><body><h1>414 URI Too Long</h1><p>The requested URI is too long for the server to process.</p></body></html>";
    errorPages[415] = "<html><body><h1>415 Unsupported Media Type</h1><p>The server does not support the media type in the request.</p></body></html>";
    errorPages[416] = "<html><body><h1>416 Range Not Satisfiable</h1><p>The range requested is not available.</p></body></html>";
    errorPages[417] = "<html><body><h1>417 Expectation Failed</h1><p>The server could not meet the expectations set in the request.</p></body></html>";
    errorPages[418] = "<html><body><h1>418 I'm a Teapot</h1><p>This is a teapot, not a coffee machine.</p></body></html>";
    errorPages[421] = "<html><body><h1>421 Misdirected Request</h1><p>The request was directed to a server that cannot produce a response.</p></body></html>";
    errorPages[422] = "<html><body><h1>422 Unprocessable Entity</h1><p>The server could not process the request due to semantic errors.</p></body></html>";
    errorPages[423] = "<html><body><h1>423 Locked</h1><p>The resource is locked.</p></body></html>";
    errorPages[424] = "<html><body><h1>424 Failed Dependency</h1><p>The request failed due to a failed dependency.</p></body></html>";
    errorPages[425] = "<html><body><h1>425 Too Early</h1><p>The server is unwilling to risk processing the request that might be replayed.</p></body></html>";
    errorPages[426] = "<html><body><h1>426 Upgrade Required</h1><p>The client must upgrade to a different protocol.</p></body></html>";
    errorPages[428] = "<html><body><h1>428 Precondition Required</h1><p>A precondition is required to complete the request.</p></body></html>";
    errorPages[429] = "<html><body><h1>429 Too Many Requests</h1><p>You have sent too many requests in a given amount of time.</p></body></html>";
    errorPages[431] = "<html><body><h1>431 Request Header Fields Too Large</h1><p>The headers are too large.</p></body></html>";
    errorPages[451] = "<html><body><h1>451 Unavailable For Legal Reasons</h1><p>This resource is unavailable for legal reasons.</p></body></html>";

    // 5xx Server Errors
    errorPages[500] = "<html><body><h1>500 Internal Server Error</h1><p>There was an error processing your request.</p></body></html>";
    errorPages[501] = "<html><body><h1>501 Not Implemented</h1><p>The server does not recognize the request method.</p></body></html>";
    errorPages[502] = "<html><body><h1>502 Bad Gateway</h1><p>The server received an invalid response from the upstream server.</p></body></html>";
    errorPages[503] = "<html><body><h1>503 Service Unavailable</h1><p>The server is currently unavailable.</p></body></html>";
    errorPages[504] = "<html><body><h1>504 Gateway Timeout</h1><p>The server did not receive a timely response from the upstream server.</p></body></html>";
    errorPages[505] = "<html><body><h1>505 HTTP Version Not Supported</h1><p>The server does not support the HTTP version in the request.</p></body></html>";
    errorPages[506] = "<html><body><h1>506 Variant Also Negotiates</h1><p>The server has an internal configuration error.</p></body></html>";
    errorPages[507] = "<html><body><h1>507 Insufficient Storage</h1><p>The server is unable to store the representation needed to complete the request.</p></body></html>";
    errorPages[508] = "<html><body><h1>508 Loop Detected</h1><p>The server detected an infinite loop while processing the request.</p></body></html>";
    errorPages[510] = "<html><body><h1>510 Not Extended</h1><p>Further extensions are required to fulfill the request.</p></body></html>";
    errorPages[511] = "<html><body><h1>511 Network Authentication Required</h1><p>Network authentication is required to access this resource.</p></body></html>";
}

std::string ErrorPage::getErrPage(int errorCode)
{
    if (errorPages.find(errorCode) != errorPages.end())
        return errorPages[errorCode];
    return "<html><body><h1>Error</h1><p>An unexpected error occurred.</p></body></html>";
}
