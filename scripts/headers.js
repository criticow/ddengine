const fs = require("fs");
const path = require("path");

const src = path.join(__dirname, "../src/ddengine");
const pchName = "ddenginepch.hpp";

let mainContent =
`#pragma once

#include <${pchName}>
`;

fs.readdir(src, {withFileTypes: true}, (err, entries) => {
  let folders = "";

  entries.forEach((entry) => {
    if(entry.isFile()) return;

    let subContent = mainContent;

    folders += `\n#include "${entry.name}/_${entry.name}.hpp"`;

    try{
      fs.rmSync(path.join(src, entry.name, `_${entry.name}.hpp`), {force: true});

      let subEntries = fs.readdirSync(path.join(src, entry.name), {withFileTypes: true});

      subEntries.forEach((subEntry) => {
        if(subEntry.isDirectory() || subEntry.name.endsWith(".cpp")) return;

        subContent += `\n#include "${subEntry.name}"`;
      })
      
      fs.writeFileSync(path.join(src, entry.name, `_${entry.name}.hpp`), subContent);
    } catch(error){
      console.log(error);
    }
  });

  try{
    fs.rmSync(path.join(src, "ddengine.hpp"), {force: true});
    fs.writeFileSync(path.join(src, "ddengine.hpp"), mainContent + folders);
  } catch(error) {
    console.log(error);
  }
})