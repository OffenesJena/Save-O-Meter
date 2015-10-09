leds = require("lamp")
leds.setup(1)
leds.init()
leds.s(15, 0xff, 0xff, 0x00)
leds.s(15, 0x00, 0x00, 0xff)
leds.finish()

leds = nil
package.loaded["lamp"]=nil
