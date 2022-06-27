import * as fs from 'fs';
import JSZip from 'jszip';
import dateFormat from 'dateformat';


const zip = new JSZip();


/// fs.rmdirSync('bundle',{ recursive: true, force: true });
if(!fs.existsSync('bundle')){
    fs.mkdirSync('bundle');
}

const dateStamp=dateFormat(new Date(), "yyyymmdd-hhMMss");

const baseFolder=`PinCommander`
console.log(baseFolder)
const files=[
    'aWOT.cpp',
    'aWOT.h',
    'PinCommander.ino',
    'secret-wifi.h',
    'StaticFiles.h',
]


files.forEach(
    filename => {
        const fullName=`${baseFolder}/${filename}`;
        try{
            zip.file(filename,fs.readFileSync(fullName));
        }catch(err){
            console.error(`${fullName} not found`);
        }
    }
)
zip.generateAsync({type:"nodebuffer"}).then(function(content) {
    // see FileSaver.js
    fs.writeFileSync(`bundle/${dateStamp}-${baseFolder}.zip`,content);
});
