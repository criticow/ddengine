const fs = require("fs");
const rm = require('fs/promises').rm;
const path = require("path");

const src = path.join(__dirname, "../src");
const includePath = path.join(__dirname, "../include/ddengine");

let mainContent =
`#pragma once

#include "../../../src/ddenginepch.hpp"
`;

fs.mkdirSync(includePath, {recursive: true});

fs.readdir(src, {withFileTypes: true}, (err, entries) => {
  let ddengineContent = mainContent;

  // Loop through entries inside the src folder
  entries.forEach((entry) => {
    // If the entry is not a folder do nothing
    if(entry.isFile()) return;

    try{
      let headerContent = mainContent;

      // Read files inside the folder to get headers
      const subEntries = fs.readdirSync(path.join(src, entry.name), {withFileTypes: true});
      
      subEntries.forEach((subEntry) => {
        // In this case return if the entry is a directory (if necessary do it recursivelly later for sub folders)
        // also dont work with anything else than .hpp files
        if(subEntry.isDirectory() || !subEntry.name.endsWith(".hpp")) return;

        headerContent += `\n#include "../../../src/${entry.name}/${subEntry.name}"`;
      });

      try{
        fs.writeFileSync(path.join(includePath, entry.name + ".hpp"), headerContent);
        ddengineContent += `\n#include "${entry.name}.hpp"`;
      }catch(error){
        console.log("Error creating file: " + entry.name + ".hpp");
      }
    }catch(error){
      console.log(error);
    }

    try{
      fs.writeFileSync(path.join(includePath, "ddengine.hpp"), ddengineContent);
    }catch(error){
      console.log("Error creating file: ddengine.hpp");
    }
  })

});