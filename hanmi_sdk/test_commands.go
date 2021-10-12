package http_request

import (
    "fmt"
)

func SendSingleRequest(input string) (bool, string) {
	req := fmt.Sprintf("control/test_single_blossom?test_input=%s", input)
    return SendGetRequest(req)
}

func SendListRequest(input string) (bool, string) {
	req := fmt.Sprintf("control/test_list_blossom?test_input=%s", input)
    return SendGetRequest(req)
}