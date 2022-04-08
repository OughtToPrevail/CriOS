global loadInterruptTable

loadInterruptTable:
  lidt [esp + 4]
  sti
  ret