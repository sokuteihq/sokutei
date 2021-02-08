const fs = require('fs')
const path = require('path')

function getLines(fileName){
    return fs.readFileSync(path.join(__dirname, fileName)).toString().split(/\r?\n/)
}

function main(){
    const compiled = []
    const mainFileLines = getLines(process.argv[2])

    mainFileLines.forEach(line => {
        if(line.startsWith('#') && line.includes('include')){
            const fileNameToOpen = line.split("\"")[1]
            const includedFileLines = getLines(fileNameToOpen)
            includedFileLines.forEach(includedLine =>{
                compiled.push(includedLine)
            }) 
        } else {
            compiled.push(line)
        }
    })

    let compiledString = ''
    
    compiled.forEach(line => {
        compiledString += line + '\n'
    })

    fs.writeFileSync('sokutei.h',  compiledString)
}
main()