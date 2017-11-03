const chips = require('avrgirl-chips-json')
const usbtinyisp = require('avrgirl-usbtinyisp')

const avrgirl = new usbtinyisp({
  debug: true,
  chip: chips.atmega328,
  programmer: 'sf-pocket-avr'
})

avrgirl.on('ready', () => {
  avrgirl.enterProgrammingMode((err) => {
    if(err){
      console.log('Error entering programming mode: ' + err)
      process.exit(1)
    }
    avrgirl.writeFlash('../build/main.hex', (err) => {
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