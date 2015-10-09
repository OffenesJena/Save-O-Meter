local moduleName = ...
local M = {}
_G[moduleName] = M

local spiport

function M.setup(port)
  spi.setup(port, spi.MASTER, spi.CPOL_LOW, spi.CPHA_LOW, spi.DATABITS_8, 0);
  spiport = port
end
 
function M.init()
    spi.send(spiport, 0x00, 0x00, 0x00, 0x00)
end

function M.s(n, b, g, r, lum)

  if (lum == nil) then
    lum = 0xff
  end

  for j = 1, n, 1 do
    spi.send(spiport, lum, b, g, r)
  end

end

function M.finish()
    spi.send(spiport, 0xff, 0xff, 0xff, 0xff)
end

return M
