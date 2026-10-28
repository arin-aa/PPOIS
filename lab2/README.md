# Лабораторная работа №2

## Предметная область

Компьютер: комплектующие, периферия, сеть, программное обеспечение, пользователи и сервисные службы.

Формат строки: `Класс | число полей | число методов | связанные классы`.

| Класс | Поля | Методы | Ассоциации (связанные классы) |
|---|---|---|---|
| Application | 3 | 2 | — |
| Battery | 3 | 2 | — |
| CPU | 5 | 2 | Sensor |
| Cable | 3 | 2 | — |
| Case | 3 | 2 | Fan |
| CompatibilityChecker | 3 | 1 | — |
| Component | 3 | 2 | — |
| Computer | 6 | 7 | Motherboard, OperatingSystem, PSU, Storage |
| Cooler | 1 | 1 | — |
| DiagnosticService | 4 | 2 | Computer, Logger |
| Driver | 3 | 2 | Component |
| Fan | 2 | 2 | — |
| File | 4 | 3 | — |
| Folder | 2 | 2 | File |
| GPU | 3 | 1 | — |
| HDD | 3 | 2 | — |
| Inventory | 4 | 2 | Component |
| IpAddress | 2 | 2 | — |
| Keyboard | 2 | 2 | — |
| Laptop | 3 | 3 | Battery |
| Logger | 4 | 2 | — |
| MacAddress | 2 | 1 | — |
| Monitor | 3 | 2 | — |
| Motherboard | 4 | 3 | CPU, RAM |
| Mouse | 2 | 2 | — |
| NVMe | 2 | 1 | — |
| NetworkInterface | 4 | 2 | IpAddress |
| OperatingSystem | 4 | 4 | Driver, Process |
| PSU | 2 | 2 | — |
| Packet | 4 | 2 | IpAddress |
| Peripheral | 3 | 2 | Port |
| Port | 3 | 2 | Cable |
| PowerConnector | 2 | 1 | — |
| Printer | 3 | 2 | File |
| Process | 3 | 2 | Application |
| RAM | 3 | 2 | — |
| Radiator | 2 | 1 | — |
| RepairTicket | 5 | 3 | Computer, Technician |
| ReportGenerator | 3 | 2 | Computer, File |
| SSD | 2 | 2 | — |
| Scanner | 3 | 1 | — |
| Sensor | 3 | 2 | — |
| Server | 4 | 3 | NetworkInterface, Packet |
| Software | 3 | 1 | — |
| Storage | 3 | 4 | — |
| SystemBuilder | 4 | 3 | CompatibilityChecker |
| Technician | 3 | 2 | Inventory |
| User | 4 | 2 | — |
| Webcam | 3 | 1 | — |
| Workstation | 2 | 2 | GPU |

### Исключения (14)

- ComputerException
- IncompatibleSocketException
- InsufficientPowerException
- OverheatingException
- DriverNotFoundException
- MemoryOverflowException
- DiskFullException
- NetworkDisconnectedException
- InvalidConfigurationException
- UnauthorizedAccessException
- BootFailureException
- PeripheralNotRespondingException
- InventoryFullException
- InvalidAddressException

### Итоговая статистика

| Показатель | Значение |
|---|---|
| Классы | 50 |
| Поля | 154 |
| Поведения | 105 |
| Ассоциации | 31 |
| Исключения | 14 |
