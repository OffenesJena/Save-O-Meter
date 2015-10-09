dht22 = require("dht22")
dht22.read(1)
t = dht22.getTemperature()
h = dht22.getHumidity()

if h == nil then
  print("Error reading from DHT22")
else
  -- floating point and integer version:
  print("Temperature: "..((t-(t % 10)) / 10).."."..(t % 10).." deg C")
  print("Humidity: "..((h - (h % 10)) / 10).."."..(h % 10).."%")
end

-- release module
dht22 = nil
package.loaded["dht22"]=nil
