#include <user_config.h>
extern "C" {
#include "apa102.h"
}
#include <SmingCore/SmingCore.h>
#include "wifi.h"

#define LED_COUNT 60

HttpServer httpd;

Timer heapTimer;

void printHeap() {
	Serial.printf("Free heap: %d bytes\r\n", system_get_free_heap_size());
}

void onFile(HttpRequest &request, HttpResponse &response) {
	String file = request.getPath();
	if (file[0] == '/')
		file = file.substring(1);

	if (file[0] == '.')
		response.forbidden();
	else {
		if (file.endsWith(".gz")) {
			response.setHeader("Content-Encoding", "gzip");
		}
		//response.setCache(86400, true); // It's important to use cache for better performance.
		response.sendFile(file);
	}
}

#ifdef SMING_HTTP_BODY
void cgi_detailedConfig(HttpRequest &request, HttpResponse &response) {
	StaticJsonBuffer<512> buffer;
	JsonArray& root = buffer.parseArray(request.getBody());
	Serial.printf("Received body %s", request.getBody());
	Serial.printf("We configure %d LEDs\r\n", root.size());
	if (!root.success()) {
		Serial.println("Error while parsing JSON array");
		response.sendString("[ERROR] Inavlid JSON");
		response.badRequest();
	}
	if (root.size() > LED_COUNT) {
		response.sendString("[ERROR] Too many LEDs");
		response.badRequest();
	}
	apa102_init(root.size());
	apa102_start();
	for (int i = 0; i < root.size(); i++) {
		JsonObject& led = root[i];
		int brightness = led["brightness"];
		int global = 0xe0 + min(brightness, 0);
		int red = led["red"];
		int green = led["green"];
		int blue = led["blue"];
		Serial.printf("Setting value for led %d: Red %d, green %d, blue %d\r\n",
				i, red, green, blue);
		apa102_set8(global, min(red, 255), min(green, 255), min(blue, 255));
	}
	apa102_stop(root.size());
}
#endif

void cgi_color(HttpRequest &request, HttpResponse &response) {
	int red = request.getQueryParameter("red", "0").toInt();
	int green = request.getQueryParameter("green", "0").toInt();
	int blue = request.getQueryParameter("blue", "0").toInt();
	int brightness = request.getQueryParameter("brightness", "0").toInt();
	apa102_init(LED_COUNT);
	apa102_start();
	int global = 0xE0 + min(brightness, 31);
	for (int i = 0; i < LED_COUNT; i++) {
		apa102_set8(global, min(red, 255), min(green, 255), min(blue, 255));
	}
	apa102_stop(LED_COUNT);
}

void initHttpd() {
	httpd.listen(80);
	httpd.addPath("/color", cgi_color);
#ifdef SMING_HTTP_BODY
	httpd.addPath("/leds", cgi_detailedConfig);
#endif
	httpd.setDefaultHandler(onFile);
}

void connectOk() {
	Serial.printf("Connected to %s with IP %s, starting http server\r\n",
			WifiStation.getSSID().c_str(),
			WifiStation.getIP().toString().c_str());
	initHttpd();
}

void init() {
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(false); // Enable debug output to serial
	Serial.println("Starting system and connecting to WiFi");
	heapTimer.initializeMs(10000, printHeap);
	heapTimer.start(true);

	WifiStation.enable(true);
	WifiStation.config(WIFI_SSID, WIFI_PWD);

	WifiStation.waitConnection(connectOk);
	Serial.printf("Setting %d LEDS on the strip\r\n", LED_COUNT);
	apa102_init(LED_COUNT);
}