flowchart TD
    A[Exécution] --> B[1. Builtins]
    A --> C[2. Commandes Externes]
    A --> D[3. Redirections]
    A --> E[4. Pipes]
    A --> F[5. Signaux]

    %% 1. Builtins
    B --> B1[Identifier Builtin]
    B --> B2[Implémenter Builtins]
    B2 --> BA[echo -n]
    B2 --> BB[cd]
    B2 --> BC[pwd]
    B2 --> BD[export]
    B2 --> BE[unset]
    B2 --> BF[env]
    B2 --> BG[exit]

    %% 2. Commandes Externes
    C --> C1[Recherche PATH]
    C --> C2[Fork Process]
    C --> C3[Execve]
    C --> C4[Wait Status]
    
    %% 3. Redirections
    D --> D1[Input <]
    D --> D2[Output >]
    D --> D3[Append >>]
    D --> D4[Heredoc <<]
    
    D1 --> D1A[Open File]
    D1 --> D1B[Dup2 STDIN]
    
    D2 --> D2A[Create/Trunc File]
    D2 --> D2B[Dup2 STDOUT]
    
    D3 --> D3A[Create/Append File]
    D3 --> D3B[Dup2 STDOUT]
    
    D4 --> D4A[Read Until Delimiter]
    D4 --> D4B[Create Temp File]
    D4 --> D4C[Dup2 STDIN]

    %% 4. Pipes
    E --> E1[Créer Pipe]
    E --> E2[Fork Process]
    E --> E3[Setup FDs]
    E --> E4[Exec Commands]
    
    %% 5. Signaux
    F --> F1[SIGINT Ctrl+C]
    F --> F2[SIGQUIT Ctrl+\]
    F --> F3[SIGTERM]

    subgraph Implementation["Ordre d'Implémentation"]
        I1[1. Builtins Simple]
        I2[2. Commandes Simple]
        I3[3. Redirections Simple]
        I4[4. Single Pipe]
        I5[5. Multiple Pipes]
        I6[6. Heredoc]
        I7[7. Signaux]
    end

    style A fill:#f9f,stroke:#333,stroke-width:4px
    style I1,I2,I3,I4,I5,I6,I7 fill:#fcf,stroke:#333
    style F1,F2,F3 fill:#ddf,stroke:#333
