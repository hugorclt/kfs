#pragma once

#include "stdint.h"

typedef struct thread_control_block {
      int     pid;
      void    *esp;
      void    *esp0;
      void    *cr3;
      struct thread_control_block *next;
      uint8_t state;
} thread_control_block_t;

thread_control_block_t *process_list_head;

void initialize_multitasking();
