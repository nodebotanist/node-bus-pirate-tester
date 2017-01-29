# Testing the bus-pirate npm module with Resin.io

When you're writing code, unit tests can be a very nice, fuzzy security blanket-- especially when paired 
with continuous integration, code coverage, and other monitoring tools.

But what do you do when you're writing code that controls hardware? Unit testing can be a nightmare, even
if you mock out the actual hardware peripheral!

But even if you get tests written, sometimes mocking out the hardware peripheral can cause more problems
than it solves-- if there's a firmware update, and you're only testing against a mock, it might be a 
while before you notice any issues!

I came across this problem when writing a library to control the [Bus Pirate]() with Node.JS-- the unit 
tests were passing, but the example code wasn't working! Turned out my mock sent an ever-so-slightly 
different response code than the actual firmware.

Eventually, the idea occurs to write tests that run against the hardware itself. But that introduces a 
whole new set of issues:

* What if you want to test multiple hardware versions of one peripheral, or test the hardware in 
different physical configurations?
* How do you make sure the hardware tests run when you push new code?
* How do you make the testing rig constantly available without carrying it around everywhere?

Luckily, [Resin.io](https://resin.io) provides an eloquent platform to launch our testing code on--

* We can launch our tester on as many devices as we need without having to manually install it on
each one-- we can have different physical configurations on each one!
* Using the public URL from the resin dashboard, we can create a git hook to run our tester at the 
same time as any of our other continuous integration solutions
* Using resin, our testing rig(s) are always available as long as they have wifi access!

## Let's get started!

First, we'll take an example test from the [bus-pirate-tester]() test suite. 
bus-pirate uses [Mocha]() for a test suite and [sinon.js]() for function spies.

```javascript
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
```