| Threads number    | Connections number | Time of response              || Carrying capacity             ||
|-------------------|--------------------|--------------|-----------------|--------------|-----------------|
|                   |                    | *with cache* | *without cache* | *with cache* | *without cache* |
| 1                 | 1                  | 92.86ms      | 44.94ms         | 161          | 131             |
| 1                 | 2                  | 60.54ms      | 33.66ms         | 232          | 181             |
| 1                 | 5                  | 123.97ms     | 131.64ms        | 270          | 230             |
| 1                 | 10                 | 151.23ms     | 178.26ms        | 270          | 230             |
| 2                 | 2                  | 42.32ms      | 49.70ms         | 131          | 90              |
| 2                 | 5                  | 107.28ms     | 114.03ms        | 151          | 121             |
| 2                 | 10                 | 155.40ms     | 268.80ms        | 171          | 130             |
| 5                 | 5                  | 91.57ms      | 106.34ms        | 80           | 60              |
| 5                 | 10                 | 249.67ms     | 190.91ms        | 70           | 60              |
| 10                | 10                 | 197.20ms     | 193.79ms        | 50           | 40              |