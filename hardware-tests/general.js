// Need to test
// constructor -- validation and success
// start -- success and failure

const assert = require('chai').assert
const sinon = require('sinon')
const fs = require('fs')
const port = '/dev/tty.usbserial-AI03KY7Z'

const BusPirate = require('../../node-bus-pirate/BusPirate.js')

describe('LIVE HARDWARE: Main BusPirate module', () => {
    let busPirate

    before(() => {
        busPirate = new BusPirate({
            port: port
        })
    })

    describe('constructor', () => {
        it('should construct when a port that exists is passed', () => {
            assert(busPirate instanceof BusPirate)
        })
    })

    describe('start()', () => {
        it('should fire the ready event when the bus pirate sends BBIO1', (done) => {
            let eventHandler = sinon.spy()

            busPirate.on('ready', () => {
                eventHandler()
            })

            busPirate.start()

            console.log(busPirate.inputQueue.buffer.toString())

            setTimeout(() => {
                assert(eventHandler.called, 'Ready event handler was not called')
                done()
            }, 1900)
        })
    })

    describe('reset()', () => {
        it('should fire a 0x00, wait for BBIO1, then fire 0x0F', (done) => {
            let writeSpy = sinon.spy(busPirate.port, 'write')
            busPirate.reset(() => {})

            setTimeout(() => {
                assert(writeSpy.called, 'reset() did not call port.write')
                assert(writeSpy.getCall(0).args[0][0] == 0x00, 'reset() did not call port.write with 0x00 first')
                assert(writeSpy.lastCall.args[0][0] == 0x0F, 'reset() did not call port.write with 0x0F second')
                done()
            }, 1900)
        })
    })
})