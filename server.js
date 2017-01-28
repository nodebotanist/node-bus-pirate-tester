var express = require('express');
var app = express();

const Mocha = require('mocha')

let mocha = new Mocha()

mocha.addFile('./test/all.js')
mocha.addFile('./hardware-tests/general.js')

let failures

function runTests() {
    mocha.run((runFailures) => {
        failures = runFailures
    })
}

runTests()

// reply to request with "Hello World!"
app.get('/', function(req, res) {
    if (failures) {
        res.sendStatus(500)
        res.end(failures.toString())
    } else {
        res.sendStatus(200)
        res.end('')
    }
});

app.get('/update', (req, res) => {

})

//start a server on port 80 and log its start to our console
var server = app.listen(80, function() {

    var port = server.address().port;
    console.log('Example app listening on port ', port);

});