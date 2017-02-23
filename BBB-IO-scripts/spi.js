const mraa = require('mraa');
const bonescript = require('bonescript');

// initialize SPI bus 0
// TODO: add CS pin usage for AUX testing
let spi = new mraa.SPI(0)

// write then check the result

// if the result is correct send response code, else error code
