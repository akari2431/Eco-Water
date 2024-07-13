import Debug "mo:base/Debug";
import Http "mo:base/Http";

actor {
    public func sendRequest(): async () {
        let url = "http://IP_DEL_ESP8266";
        let request = Http.Request(url, #get, null, Http.Headers([]));
        
        try {
            let response = await Http.fetch(request);
            switch (response.status) {
                case (#ok):
                    let body = await response.body;
                    Debug.print(debug_show(body));
                case _:
                    Debug.print("Error al realizar la solicitud");
            };
        } catch (error) {
            Debug.print("Error de conexión: " # debug_show(error));
        };
    };
};