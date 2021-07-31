// Script to load BotW CSV data into Ghidra
//@author AlexApps99
//@category BotW

import ghidra.app.script.GhidraScript;
import ghidra.program.model.symbol.SourceType;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.app.cmd.label.DemanglerCmd;
import ghidra.program.model.address.AddressSet;
import ghidra.util.NumericUtilities;
import ghidra.app.cmd.label.DemanglerCmd;
import ghidra.program.model.listing.FunctionTag;
import ghidra.util.exception.DuplicateNameException;
import ghidra.program.model.listing.FunctionTagManager;

public class RenameFunctionsInGhidra extends GhidraScript {
    private FunctionManager func_mgr;
    private FunctionTagManager func_tag_mgr;
    private String ok;
    private String minor;
    private String major;
    private String wip;
    private String undecompiled;
    private String lib;

    private FunctionTag getOrMake(String name) {
        FunctionTag f = func_tag_mgr.getFunctionTag(name);
        if (f == null) f = func_tag_mgr.createFunctionTag(name, null);
        return f;
    }

    @Override
    public void run() throws Exception {
        func_mgr = currentProgram.getFunctionManager();
        func_tag_mgr = func_mgr.getFunctionTagManager();
        ok = getOrMake("OK").getName();
        minor = getOrMake("MINOR").getName();
        major = getOrMake("MAJOR").getName();
        wip = getOrMake("WIP").getName();
        undecompiled = getOrMake("UNDECOMPILED").getName();
        lib = getOrMake("LIBRARY").getName();


        File input_csv = askFile("uking_functions.csv", "Go");
        try (BufferedReader br = new BufferedReader(new FileReader(input_csv))) {
            // Skip header
            String line = br.readLine();
            while ((line = br.readLine()) != null) {
                String[] pieces = line.split(",", -4); // Don't skip empty last column
                if (pieces.length != 4) throw new Exception("Invalid CSV row: " + line);

                Address addr = toAddr(pieces[0]);
                String status = pieces[1];
                long func_size = func_size = NumericUtilities.parseLong(pieces[2].strip());

                String name = pieces[3].strip();

                Function func = applyFunction(addr, status, name, func_size);
            }
        }
    }


    // TODO the j_ prefix probably breaks demangling
    private Function applyFunction(Address addr, String status, String name, long func_size) throws Exception {
        if (name.isEmpty()) name = null;

        Function func = func_mgr.getFunctionAt(addr);
        AddressSet body = new AddressSet(addr, addr.addNoWrap(func_size - 1));


        if (func != null) {
            // Demangling can break this, hence the try-catch
            try {
                if (func.getName() != name) func.setName(name, SourceType.IMPORTED);
            } catch (DuplicateNameException e) {}
            if (!func.getBody().hasSameAddresses(body)) {
                func.setBody(body);
            }
        } else {
            func = func_mgr.createFunction(name, addr, body, SourceType.IMPORTED);
        }

        if (name != null) {
            DemanglerCmd cmd = new DemanglerCmd(addr, name);
            if (!cmd.applyTo(currentProgram, monitor)) {
                // Something that isn't mangled
            }
        }

        func.removeTag(ok);
        func.removeTag(minor);
        func.removeTag(major);
        func.removeTag(wip);
        func.removeTag(undecompiled);
        func.removeTag(lib);
        if (status.equals("O")) {
            func.addTag(ok);
        } else if (status.equals("m")) {
            func.addTag(minor);
        } else if (status.equals("M")) {
            func.addTag(major);
        } else if (status.equals("W")) {
            func.addTag(wip);
        } else if (status.equals("L")) {
            func.addTag(lib);
            func.addTag(undecompiled);
        } else {
            func.addTag(undecompiled);
        }

        return func;
    }
}