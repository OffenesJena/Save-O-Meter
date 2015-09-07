#ESP8266 Software


## Debugging the LED strip

1.) Connect via the USB2Serial adapter

2.) Init the SPI port
```lua
    spi.setup(1, spi.MASTER, spi.CPOL_LOW, spi.CPHA_LOW, spi.DATABITS_8, 0);
```

3.) Send the dotStar LED strip init sequence
```lua
    spi.send(1, 0x00, 0x00, 0x00, 0x00)
```

4.) Repeat the following BGR sequence for every LED of the LED strip    
   The syntax is (SPIId, global brightness, BLUE, GREEN, RED)    
   Be aware that the LED strip is a shift register, therefore the last write will not be visible until you write the next values.
```lua
    spi.send(1, 0xff, 0x00, 0x00, 0xff)
```

5.) Send the dotStar LED strip finish sequence    
   For more than 60 LEDs this sequence might need more bytes.
```lua
    spi.send(1, 0xff, 0xff, 0xff, 0xff)
```

## Send a rainbow

The following code uses a LUA function to send rainbow colors to the LED string.

```lua
function rainbow(NumberOfLEDs)

	spi.send(1, 0x00, 0x00, 0x00, 0x00)
	
	for j = 1, NumberOfLEDs/10, 1 do
		spi.send(1, 0xff, 0x00, 0x00, 0xff)
		spi.send(1, 0xff, 0x00, 0xaa, 0xdd)
		spi.send(1, 0xff, 0x00, 0xdd, 0xaa)
		spi.send(1, 0xff, 0x00, 0xff, 0x00)
		spi.send(1, 0xff, 0xaa, 0xdd, 0x00)
		spi.send(1, 0xff, 0xdd, 0xaa, 0x00)
		spi.send(1, 0xff, 0xff, 0x00, 0x00)
		spi.send(1, 0xff, 0xdd, 0x00, 0xaa)
		spi.send(1, 0xff, 0xbb, 0x00, 0xcc)
		spi.send(1, 0xff, 0xaa, 0x00, 0xdd)
	end
	
	spi.send(1, 0xff, 0xff, 0xff, 0xff)
	
end
```

The code expects the total number of LEDs in the string as the first parameter for the function call. Therefore the syntax for calling the function for a 60 LED strip is:

```lua
rainbow(60)
```
