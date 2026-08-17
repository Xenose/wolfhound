#ifndef _wnt_header_signal_
#define _wnt_header_signal_

typedef struct {
   unsigned short control_word;
   unsigned short status_word;
   unsigned char tag_word;
   unsigned char reserved1;
   unsigned short error_opcode;
   unsigned long error_offset;
   unsigned short error_selector;
   unsigned short reserved2;
   unsigned long data_offset;
   unsigned short data_selector;
   unsigned short reserved3;
   unsigned long mx_csr;
   /*
    * FloatRegisters: [M128A; 8]
    * XmmRegisters: [M128A; 16]
    * Reserved4: [u8; 96]
    */
} _wnt_xsave_format_s;

typedef struct {
   unsigned long long p1_home;
   unsigned long long p2_home;
   unsigned long long p3_home;
   unsigned long long p4_home;
   unsigned long long p5_home;
   unsigned long long p6_home;

   unsigned long context_flags;
   unsigned long mx_csr;

   unsigned short seg_cs;
   unsigned short seg_ds;
   unsigned short seg_es;
   unsigned short seg_fs;
   unsigned short seg_gs;
   unsigned short seg_ss;
   
   unsigned long e_flags;

   unsigned long long dr0;
   unsigned long long dr1;
   unsigned long long dr2;
   unsigned long long dr3;
   unsigned long long dr4;
   unsigned long long dr5;
   unsigned long long dr6;
   unsigned long long dr7;

   unsigned long long rax;
   unsigned long long rcx;
   unsigned long long rdx;
   unsigned long long rbx;
   unsigned long long rsp;
   unsigned long long rbp;
   unsigned long long rsi;
   unsigned long long rdi;
   unsigned long long r8;
   unsigned long long r9;
   unsigned long long r10;
   unsigned long long r11;
   unsigned long long r12;
   unsigned long long r13;
   unsigned long long r14;
   unsigned long long r15;
   unsigned long long rip;

   union {
      _wnt_xsave_format_s flt_save;
   } dummy_union_name;

} _wnt_exception_context_s;

typedef struct _wnt_exception_record_s {
   unsigned long exception_code;
   unsigned long exception_flags;
   _wnt_exception_record_s* record;
   void* exception_address;
   unsigned long number_parameters;
   unsigned long* exception_information[1024];
} _wnt_exception_record_s;

typedef struct {
   _wnt_exception_record_s exception_record;
   _wnt_exception_context_s context_record;
} _wnt_exception_pointers_s;

extern int _wnt_set_console_ctrl_handler(int (*handler)(unsigned int), short add);
extern void* _wnt_add_vectored_exception_handler(unsigned long first, long (*func)(_wnt_exception_pointers_s*));

#endif /* _wnt_header_signal */
