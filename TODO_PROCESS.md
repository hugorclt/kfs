# TODO — Process implementation

## Phase 0 — fix rapide avant de commencer

- [ ] `system.asm` (`system_handler_wrapper`, lignes 26-28) : appelle toujours `panic` après le handler, même pour Debug/Breakpoint (int 1, 3). Toute exception halt la machine. Prévoir retour normal (`iret`) sur exceptions non-fatales.
- [ ] `process.h` (ligne 14) : `process_list_head` déclaré sans `extern` (tentative definition). Ajouter `extern` dans le header + définition dans le `.c`, avant d'inclure `process.h` dans plusieurs fichiers (scheduler.c etc).

## Phase 1 — Timer (PIT, IRQ0)

- [ ] Programmer le PIT (port 0x40/0x43, channel 0, mode 3) à fréquence fixe (ex 100Hz).
- [ ] Ajouter handler IRQ0 dans `handler_hardware.c` (suivre le pattern `keyboard_init`/`keyboard_handler`).
- [ ] Compteur de ticks global, base pour futur `sleep`/scheduling.

## Phase 2 — TSS par process

- [ ] `gdt.c` (`tss_entry.esp0`, ligne 52) : mis à jour une seule fois au boot. Doit être mis à jour à chaque switch. Fonction genre `tss_set_esp0(uint32_t esp0)` appelée par le scheduler.

## Phase 3 — Context switch (asm)

- [ ] Nouveau fichier asm : sauver registres du process courant (pusha + segments), sauver `esp` dans le TCB, charger `cr3` du nouveau process, charger son `esp`, restaurer registres, `ret`/`iret` vers le nouveau contexte.
- [ ] `thread_control_block_t` a déjà `esp`/`esp0`/`cr3` (`process.h` ligne 5) — struct prête, seul le code de switch manque.

## Phase 4 — page mapping user + page fault réel

- [ ] `vmm.c` (`vmm_map_page`, ligne 104) : hardcode flags Present+RW supervisor. Ajouter variante avec flag USER pour charger le code d'un process en ring3.
- [ ] `handler_system.c` (case 14, ligne 46) : lire CR2 (adresse fautive), décider kill process ou grow stack, plutôt que print + panic.

## Phase 5 — Scheduler

- [ ] Ready queue (liste de `thread_control_block_t`, champ `next` déjà présent).
- [ ] Round-robin basique : sur tick timer, sauver contexte courant, pick next dans la queue, context switch.
- [ ] Champ `state` (`process.h` ligne 11) est juste un `uint8_t` sans enum — définir READY/RUNNING/BLOCKED/ZOMBIE.

## Phase 6 — fork/exit basique

- [ ] `fork()` : nouveau `cr3` (copie ou COW du page directory), nouveau TCB, PID counter.
- [ ] `exit()`/cleanup : `kfree` du TCB, libérer les pages du process (`vmm_free_page` en boucle), retirer de la ready queue.
- [ ] Brancher `initialize_multitasking()` dans `main.c` — actuellement jamais appelé.

## Doc

**PIT / timer**
- OSDev wiki — Programmable Interval Timer: https://wiki.osdev.org/Programmable_Interval_Timer
- OSDev wiki — IRQ: https://wiki.osdev.org/IRQ

**Context switch / TSS**
- OSDev wiki — Context Switching: https://wiki.osdev.org/Context_Switching
- OSDev wiki — Task State Segment: https://wiki.osdev.org/Task_State_Segment
- OSDev wiki — Getting to Ring 3: https://wiki.osdev.org/Getting_to_Ring_3

**Scheduler / multitasking**
- OSDev wiki — Kernel Multitasking: https://wiki.osdev.org/Kernel_Multitasking
- OSDev wiki — Scheduling Algorithms: https://wiki.osdev.org/Scheduling_Algorithms
- BrokenThorn OS Dev Series, Part 15 (Multitasking): http://www.brokenthorn.com/Resources/OSDev19.html (index: http://www.brokenthorn.com/Resources/OSDevIndex.html)

**Page fault / paging avancé (COW)**
- OSDev wiki — Page Fault: https://wiki.osdev.org/Page_Fault
- OSDev wiki — Copy-on-Write: https://wiki.osdev.org/Copy_on_Write

**fork/exec**
- OSDev wiki — Fork: https://wiki.osdev.org/Fork