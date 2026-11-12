from dataclasses import dataclass

@dataclass
class server_c:
    ip: str
    port: str = "6666"
    name: str = "no_name"
