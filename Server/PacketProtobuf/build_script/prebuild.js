var fs = require('fs');
var execSync = require('child_process').execSync;
var spawnSync = require('child_process').spawnSync;
var os = require('os');

// Generate cpp & csharp files from .proto files
try {
    fs.statSync('../src_proto')
}
catch(err) {
    fs.mkdirSync('../src_proto');
}

try{
    fs.statSync('../../../Client/Assets/Script/PacketMsg');
}
catch(err) {
    fs.mkdirSync('../../../Client/Assets/Script/PacketMsg');
}

var protoc = '';

if(os.platform() == 'win32') {
    protoc = '..\\protoc\\protoc';
} else {
    protoc = 'protoc';
}

var cppOutput = execSync(protoc + ' --proto_path=../proto --cpp_out=../src_proto --descriptor_set_out=../src_proto/proto.protobin ../proto/enum/*.proto ../proto/struct/*.proto ../proto/etc/*.proto');
console.log(cppOutput.toString());

if(os.platform() == 'win32') {
    var csharpOutput = spawnSync('../protoc/ProtoGen',
    [
        String.raw`-o:..\..\..\Client\Assets\Script\PacketMsg\PacketProtobuf.cs`,
        String.raw`-i:..\src_proto\proto.protobin`
    ]);

    console.log(csharpOutput.stdout.toString());
    console.log(csharpOutput.stderr.toString());
}
