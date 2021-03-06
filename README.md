[![npm version](https://badge.fury.io/js/homebridge-http-environmentals.svg)](https://badge.fury.io/js/homebridge-http-environmentals)
# homebridge-http-environmentals

A HTTP(S) environmental monitoring accessory for [Homebridge](https://github.com/nfarina/homebridge).

Forked from [lucacri/homebridge-http-temperature-humidity](https://github.com/lucacri/homebridge-http-temperature-humidity)

# Installation

1. Install homebridge using: `npm install -g homebridge`
2. Install this plugin using: `npm install -g homebridge-http-environmentals`
3. Update your configuration file. See `sample-config.json` in this repository for a sample.

# Configuration

Sample configuration:

```
"accessories": [
    {
        "accessory": "HttpEnvironmentals",
        "name": "Living Room Environmentals",
        "url": "http://192.168.1.210/sensors",
        "httpMethod": "GET",
        "cacheExpiration": 60
    }
]
```

The `cacheExpiration` option specifies, in seconds, how long HTTP responses will be stored in the in-memory cache.

---

Your HTTP(S) endpoint should produce JSON that looks like this:

```
{
    "temperature": 25.8,
    "humidity": 38,
    "pressure": 1011
}
```

---

**This plugin only acts as an interface between a web endpoint and Homebridge.** You will still need some dedicated hardware to expose the web endpoints with the sensor information. There is a code sample for ESP8266 with an MPL3115A2 pressure sensor.  This will be updated with Bosch BME280 support soon once my sensor arrives as I've found the DHTXX sensors to be inacurate/unreliable. 
