#! /usr/bin/node
const argv = require('yargs')
.options({
  'programmer': {
    alias: 'p',
    describe: 'the type of programmer you are using',
    default: 'sf-pocket-avr'
  },
  'chip': {
    alias: 'c',
    describe: 'the chip that you are checking for the signature of',
    demandOption: true
  }
}).argv
const chips = require('avrgirl-chips-json')
const usbtinyisp = require('avrgirl-usbtinyisp')

const chip = chips[argv.chip]
if(!chip){
  console.log('ERROR: invalid chip (not recognized by avrgirl-chips-json)')
  process.exit(1)
}

const avrgirl = new usbtinyisp({
  debug: false,
  chip: chip,
  programmer: argv.programmer
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
      const expectedSig = new Buffer(chip.sig)
      const actualSig = new Buffer(sig)
      if(!actualSig.equals(expectedSig)){
        console.log('Expected signature ', expectedSig, ' does not match chip signature ', actualSig);
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