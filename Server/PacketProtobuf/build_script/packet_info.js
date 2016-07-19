var fs = require('fs');
var execSync = require('child_process').execSync;

// Init npm if not already init
try {
    fs.statSync('node_modules')
}
catch(err) {
    execSync('npm install');
}

var ProtoBuf = require('protobufjs');
var ejs = require('ejs');

try {
    fs.statSync('../Autogen')
}
catch(err) {
    fs.mkdirSync('../Autogen');
}

var rootProtoDir = '../proto/';
var enumProtoDir = 'enum/';
var structProtoDir = 'struct/';

var enumProtoList = fs.readdirSync(rootProtoDir + enumProtoDir);
var structProtoList = fs.readdirSync(rootProtoDir + structProtoDir);

var enumRootList = [];
var structRootList = [];

for (var i in enumProtoList) {
    var builder = ProtoBuf.loadProtoFile({
        root: rootProtoDir,
        file: enumProtoDir + enumProtoList[i]}
        );
    enumRootList.push(builder.build());
}

for (var i in structProtoList) {
    var builder = ProtoBuf.loadProtoFile({
        root: rootProtoDir,
        file: structProtoDir + structProtoList[i]
    });
    structRootList.push(builder.build());
}

var enumList = {};
var structList = {};

// Parse enum first
for (var i in enumRootList) {
    var enumRoot = enumRootList[i];

    for (var enumTypeName in enumRoot.PKENUM) {
        var regex = new RegExp(/^(.*)PacketEnum$/);
        var match = enumTypeName.match(regex);

        if (match === null) {
            continue;
        }

        var namespace = match[1];
        enumList[namespace] = {};

        for (var enumName in enumRoot.PKENUM[enumTypeName]) {
            var prefix = namespace + '_';
            if (enumName.indexOf(prefix) != 0) {
                continue;
            }

            var enumTrueName = enumName.replace(prefix, '');
            enumList[namespace][enumTrueName] = enumRoot.PKENUM[enumTypeName][enumName];
        }
    }
}

// Parse struct next
for (var namespace in enumList) {
    var prefix = namespace + '_';

    for (var i in structRootList) {
        var structRoot = structRootList[i];

        for (var structName in structRoot.PKS) {
            if (structName.indexOf(prefix) != 0) {
                continue;
            }

            var structTrueName = structName.replace(prefix, '');
            if (enumList[namespace][structTrueName] === undefined) {
                continue;
            }

            if (structList[namespace] === undefined) {
                structList[namespace] = [];
            }

            structList[namespace].push(structTrueName);
        }
    }
}

var list = [];

// Final data struct for ejs template
for (var namespace in structList) {
    for (var i in structList[namespace]) {
        var trueName = structList[namespace][i];
        var enumNamespaceList = enumList[namespace];

        var enumType = 'PKENUM::' + namespace + 'PacketEnum';
        var enumName = enumType + '::' + namespace + '_' + trueName;
        var structName = 'PKS::' + namespace + '_' + trueName;

        var ejsStruct = {
            pksName: structName,
            enumType: enumType,
            enumName: enumName
        };

        list.push(ejsStruct);
    }
}

ejs.renderFile('PksInfo.ejs', { list: list }, function (err, str) {
    fs.writeFile('../Autogen/PksInfo.h', str);
});

ejs.renderFile('PkEnumInfo.ejs', { list: list }, function (err, str) {
    fs.writeFile('../Autogen/PkEnumInfo.h', str);
});