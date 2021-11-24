package http_request

import (
    "fmt"
)

func CreateUser_Request(uuid string, pw string) (bool, string) {
	var jsonBody = fmt.Sprintf("{uuid:%s,pw:%s}", uuid, pw)
	path := "control/misaka/create_user"
	vars := ""
    return SendPost_Request(path, vars, jsonBody)
}

func GetUser_Request(user_name string) (bool, string) {
	path := "control/misaka/user"
	vars := fmt.Sprintf("&user_name=%s", user_name)
    return SendGet_Request(path, vars)
}

func ListUser_Request() (bool, string) {
	path := fmt.Sprintf("control/misaka/users")
	vars := ""
    return SendGet_Request(path, vars)
}
