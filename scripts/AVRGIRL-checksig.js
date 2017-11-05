#! /usr/bin/node
const argv = require('yargs').argv
const chips = require('avrgirl-chips-json')
const usbtinyisp = require('avrgirl-usbtinyisp')

const avrgirl = new usbtinyisp({
  debug: false,
  chip: chips.atmega328,
  programmer: 'sf-tiny-avr'
})

avrgirl.on('ready', () => {
  avrgirl.enterProgrammingMode((err) => {
    if(err){
      console.log('Error entering programming mode: ' + err)
      process.exit(1)
    }
    avrgirl.getChipSignature((err, sig) => {
      if(err){
        console.log('Error getting chip signature: ' + err)
        process.exit(1)
      }
      const expectedSig = new Buffer([30, 149, 15])
      if(!new Buffer(sig).equals(expectedSig)){
        console.log('Expected signature ', expectedSig, ' does not match chip signature ', new Buffer(sig));
        process.exit(1)
      }
      console.log('Chip signature matched!')
      avrgirl.exitProgrammingMode((err) => {
        if(err){
          console.log('Error exiting programming mode: ' + err)
          process.exit(1)
        }
      })
    })
  })
})