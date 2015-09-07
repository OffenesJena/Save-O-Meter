#ESP8266 Software

1. Connect via the USB2Serial adapter

2. Init the SPI port
```lua
    spi.setup(1, spi.MASTER, spi.CPOL_LOW, spi.CPHA_LOW, spi.DATABITS_8, 0);
```

3. Send the dotStar LED strip init sequence
```lua
    spi.send(1, 0x00, 0x00, 0x00, 0x00)
```

4. Repeat the following BGR sequence for every LED of the LED strip    
   The syntax is (SPIId, global brightness, BLUE, GREEN, RED)
```lua
    spi.send(1, 0xff, 0x00, 0x00, 0xff)
```

5. Send the dotStar LED strip finish sequence    
   For more than 60 LEDs this sequence might need more bytes.
```lua
    spi.send(1, 0xff, 0xff, 0xff, 0xff)
```
