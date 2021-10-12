package http_request

import (
    "fmt"
    "net/http"
    "io/ioutil"
    "crypto/tls"
	"strings"
	"strconv"
    "os"
)

func SendGetRequest(path string) (bool, string) {
    return sendRequest("get", path)
}

func sendRequest(requestType string, path string) (bool, string) {
    // read environment-variables
	var address = os.Getenv("HANAMI_ADDRESS")
	port, err := strconv.Atoi(os.Getenv("HANAMI_PORT"))
    if err != nil {
        return false, "err"
    }

    // check if https or not
	if strings.Contains(address, "https") {
		http.DefaultTransport.(*http.Transport).TLSClientConfig = &tls.Config{InsecureSkipVerify: true}
	}

    // send get-request
    if requestType == "get" {
        resp, err := http.Get(fmt.Sprintf("%s:%d/%s", address, port, path))
        if err != nil {
            panic(err)
        }
        defer resp.Body.Close()
    
        // read data from response and convert into string
        bodyBytes, err := ioutil.ReadAll(resp.Body)
        if err != nil {
            return false, ""
        }
        bodyString := string(bodyBytes)
    
        return true, bodyString
    }

    return false, ""
}
