#ESP8266 Software


## Debugging the LED strip

1.) Connect via the USB2Serial adapter

2.) Init the SPI port
```lua
    spi.setup(1, spi.MASTER, spi.CPOL_LOW, spi.CPHA_LOW, spi.DATABITS_8, 0);
```

3.) Define and send the dotStar LED strip init sequence
```lua

    function initLEDs()
        spi.send(1, 0x00, 0x00, 0x00, 0x00)
    end

    initLEDs()    
    
```

4.) Repeat the following BGR sequence for every LED of the LED strip    
   The syntax is `spi.send(SPIId, global_brightness, BLUE, GREEN, RED)`   
   Be aware that the data forwarding inside the LED strip is organized as a shift register. This means the first color values sent will define the color of the first LED, the **second color values sent** will define the **color of the second LED**... an so on. But not the colors values get shifted (the first color values will not move a long the LED strip), but the internal data forwarding is like a shift register.
```lua
    spi.send(1, 0xff, 0x00, 0x00, 0xff)
```

Lazy people can write a simple LUA function to send color values to multiple LEDs at once
    
```lua
    function s(n, b, g, r, lum)

        if (lum == nil) then
            lum = 0xff
        end

        for j = 1, n, 1 do
            spi.send(1, lum, b, g, r)
        end
	
    end
```

5.) Send the dotStar LED strip finish sequence    
   The data forwarding within the LED strip introduces some delay of at least one cycle. This means: If you send 15 color values, just 14 will be visible immediately. For the last one you have to send at least one additional color value. This *last values* are also called *finish sequence* and is defined as a collection of at least four 0xff bytes. For more than 60 LEDs this sequence might need more bytes.
```lua
    spi.send(1, 0xff, 0xff, 0xff, 0xff)
```

6.) Send new colors    
    When you want to change the colors, just send a new init sequence `initLEDs()` and the new color values.

## Send a rainbow

The following code uses a LUA function to send rainbow colors to the LED string.

<img src="rainbow.jpg" alt="lamp" width="800px" height="180px">

```lua
function rainbow(NumberOfLEDs)

	spi.send(1, 0x00, 0x00, 0x00, 0x00)
	
	for j = 1, NumberOfLEDs/12+1, 1 do
		spi.send(1, 0xff, 0x00, 0x00, 0xff)
		spi.send(1, 0xff, 0x00, 0x7f, 0xff)
		spi.send(1, 0xff, 0x00, 0xff, 0xff)
		spi.send(1, 0xff, 0x00, 0xff, 0x7f)
		spi.send(1, 0xff, 0x00, 0xff, 0x00)
		spi.send(1, 0xff, 0x7f, 0xff, 0x00)
		spi.send(1, 0xff, 0xff, 0xff, 0x00)
		spi.send(1, 0xff, 0xff, 0x7f, 0x00)
		spi.send(1, 0xff, 0xff, 0x00, 0x00)
		spi.send(1, 0xff, 0xff, 0x00, 0x7f)
		spi.send(1, 0xff, 0xff, 0x00, 0xff)
		spi.send(1, 0xff, 0x7f, 0x00, 0xff)	
	end
	
	spi.send(1, 0xff, 0xff, 0xff, 0xff)
	
end
```

The code expects the total number of LEDs in the string as the first parameter for the function call. Therefore the syntax for calling the function for a 60 LED strip is:

```lua
rainbow(60)
```
