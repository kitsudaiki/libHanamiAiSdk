package http_request

import (
    "fmt"
)

func CreateUser_Request(uuid string, pw string) (bool, string) {
	var jsonBody = fmt.Sprintf("{uuid:%s,pw:%s}", uuid, pw)
	req := "control/misaka/create_user"
    return SendPost_Request(req, jsonBody)
}

func GetUser_Request(user_name string) (bool, string) {
	req := fmt.Sprintf("control/misaka/user?user_name=%s", user_name)
    return SendGet_Request(req)
}