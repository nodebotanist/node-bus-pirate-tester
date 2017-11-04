const path = require('path')
const chips = require('avrgirl-chips-json')
const usbtinyisp = require('avrgirl-usbtinyisp')

/* Workaround until my PRs go through for avrgirl-chips-json */
let chip = chips.atmega328p
chip.flash.pageSize = 128
chip.flash.pages = 256

const avrgirl = new usbtinyisp({
  debug: true,
  chip: chip,
  programmer: 'sf-pocket-avr'
})

avrgirl.on('ready', () => {
  avrgirl.enterProgrammingMode((err) => {
    if(err){
      console.log('Error entering programming mode: ' + err)
      process.exit(1)
    }
    avrgirl.eraseChip((err) => {
      if(err){
        console.log('Error erasing chip: ' + err)
        process.exit(1)
      }
      avrgirl.writeFlash(path.resolve('build/main.hex'), (err) => {
        if(err){
          console.log('Error flashing code: ' + err)
          process.exit(1)
        }
        avrgirl.exitProgrammingMode((err) => {
          if(err){
            console.log('Error exiting programming mode: ' + err)
            process.exit(1)
          }
        })
      })
    })
  })
})