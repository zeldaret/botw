import idaapi

for i in range(idaapi.get_fchunk_qty()):
    chunk = idaapi.getn_fchunk(i)
    if not idaapi.is_func_tail(chunk):
        continue

    ea = chunk.start_ea
    print("removing tail 0x%016x" % ea)
    parent = idaapi.get_func(ea)
    idaapi.remove_func_tail(parent, ea)
    idaapi.add_func(ea)
