
                [ Start Simulation ]
                         │
                         ▼
              [ Scan Target Directory ]
                         │
                         ▼
             [ Identify All Normal Files ]
                         │
                         ▼
             [ Simulated Encryption Loop ]
        ┌────────────────────────────────────┐
        │  - Read file into memory           │
        │  - Apply placeholder transformation│
        │  - Write modified data             │
        └────────────────────────────────────┘
                         │
                         ▼
                [ Rename to *.locked ]
                         │
                         ▼
         [ User Attempts to Open File ]
                         │
            ┌────────────┴──────────────┐
            │                           │
            ▼                           ▼
     [ If .locked ]               [ If normal file ]
  Show warning popup           Allow access message
            │                           │
            └────────────┬──────────────┘
                         ▼
                [ Simulation Complete ]
