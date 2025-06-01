;; Memory map I/O:
;; uint_binary_size, binary {0, 0xFFFFF}
;; uint_js_memory {0x100000, 0x200000 - 1}

(module
    ;; Imports
    (import "env" "log" (func $log (param i32)))
    ;; Global variables
    (global $uint_success i32 (i32.const 0))
    (global $uint_error i32 (i32.const 1))
    (global $uint_size (export "uint_size") i32 (i32.const 4))
    (global $uint_destination_size (export "uint_destination_size") i32 (i32.const 0x100000))
    (global $uint_destination (export "uint_destination") i32 (i32.const 0))
    (global $uint_memory_size (export "uint_memory_size") i32 (i32.const 0x200000))
    (global $uint_js_memory (export "uint_js_memory") i32 (i32.const 0x100000))
    (global $uint_js_memory_size (export "uint_js_memory_size") i32 (i32.const 0x100000))

    ;; memory
    (memory (export "uint_memory") 32) ;; @NOTE: uint_memory_size

    (func $compile (export "compile")
        (param $uint_source_size i32)
        (param $uint_source i32)
        (result i32)

        ;; Variables declaration
        (local $uint_i i32)
        (local $uint_j i32)

        ;; Variables definition
        i32.const 0
        local.set $uint_i
        i32.const 0
        local.set $uint_j

        (block $exit
            ;; uint_i = 4;
            i32.const 0
            local.set $uint_i

            (loop $loop
                ;; if(uint_i >= uint_source_size) { break; }
                local.get $uint_i
                local.get $uint_source_size
                i32.ge_u
                br_if $exit

                ;; uint_destination + uint_index;
                global.get $uint_destination
                i32.const 4
                i32.add
                local.get $uint_i
                i32.add
                ;; uint_source + uint_index;
                local.get $uint_source
                local.get $uint_i
                i32.add
                ;; *uint_destination++ = *uint_source++;
                i32.load8_u
                i32.store

                ;; i++;
                local.get $uint_i
                i32.const 1
                i32.add
                local.set $uint_i

                br $loop
            )
        )

        global.get $uint_destination
        local.get $uint_i
        i32.store

        global.get $uint_success
    )

    (func $main (export "main")
        (param $uint_source_size i32)
        (param $uint_source i32)
        (result i32)

        local.get $uint_source_size
        local.get $uint_source
        call $compile
    )
)