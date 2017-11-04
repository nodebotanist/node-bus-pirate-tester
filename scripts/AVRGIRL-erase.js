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
    avrgirl.eraseChip((err) => {
      if(err){
        console.log('Error erasing chip: ' + err)
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