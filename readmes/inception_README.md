# Inception — Production-Ready Containerized Web Infrastructure

[![Docker](https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white)](https://www.docker.com/)
[![Nginx](https://img.shields.io/badge/NGINX-009639?style=for-the-badge&logo=nginx&logoColor=white)](https://nginx.org/)
[![WordPress](https://img.shields.io/badge/WordPress-21759B?style=for-the-badge&logo=wordpress&logoColor=white)](https://wordpress.org/)
[![MariaDB](https://img.shields.io/badge/MariaDB-003545?style=for-the-badge&logo=mariadb&logoColor=white)](https://mariadb.org/)
[![Debian](https://img.shields.io/badge/Debian-A81D33?style=for-the-badge&logo=debian&logoColor=white)](https://www.debian.org/)
[![Security](https://img.shields.io/badge/TLS%201.3-Enforced-success?style=for-the-badge&logo=letsencrypt&logoColor=white)]()

> A DevOps and Systems Administration portfolio project demonstrating microservices orchestration, container security, automated bootstrap scripting, custom image compilation, and secure network isolation using **Docker** and **Docker Compose**.

---

## 📌 Executive Summary

Modern web platforms demand high availability, strict security boundaries, and reproducible deployments. **Inception** is a multi-container web infrastructure built completely from scratch. 

Rather than relying on pre-packaged, black-box DockerHub images, every component (Reverse Proxy, Web Server, Database) is compiled locally from minimal `debian:bookworm` base images. The architecture enforces zero-trust process isolation: the only public entrance to the entire stack is an encrypted HTTPS endpoint. All backend communication happens over a private, software-defined virtual network.

### 🌟 Key Project Highlights
- **100% Custom Base Builds**: Built from raw Debian base images with explicitly managed dependencies and configurations.
- **Strict HTTPS Entrypoint**: Only port `443` is exposed to the outside world, enforcing modern **TLS 1.2** and **TLS 1.3** protocols.
- **Zero Exposed Backend Ports**: Database (MariaDB) and Application (PHP-FPM) services operate in complete isolation without public network exposure.
- **Secrets Management**: Credentials and sensitive database passwords are non-persistently mounted via **Docker Secrets** (`/run/secrets/`), avoiding environment variable leak risks.
- **Automated Deployment**: One-command initialization via `Makefile` and `docker compose`, with automated WP-CLI configuration and database initialization scripts.
- **Persistent Data Storage**: Persistent host volumes guarantee site data and database records survive container destruction and redeployment.

---

## 🏗️ System Architecture

```text
                                [ Public Internet ]
                                         │
                                  HTTPS (Port 443)
                                TLS 1.2 / TLS 1.3
                                         │
   ┌─────────────────────────────────────▼─────────────────────────────────────┐
   │                            NGINX Container                                │
   │                   (TLS Termination & Reverse Proxy)                       │
   └─────────────────────────────────────┬─────────────────────────────────────┘
                                         │
                         Internal Bridge Network (FastCGI :9000)
                                         │
   ┌─────────────────────────────────────▼─────────────────────────────────────┐
   │                       WordPress + PHP-FPM Container                       │
   │               (Application Server / WP-CLI Automated Setup)               │
   └─────────────────────────────────────┬─────────────────────────────────────┘
                                         │
                          Internal Bridge Network (MySQL :3306)
                                         │
   ┌─────────────────────────────────────▼─────────────────────────────────────┐
   │                             MariaDB Container                             │
   │                          (SQL Database Engine)                            │
   └───────────────────────────────────────────────────────────────────────────┘
                                         │
                    ┌────────────────────┴────────────────────┐
                    ▼                                         ▼
         WordPress Host Volume                     MariaDB Host Volume
       (/home/${USER}/data/wordpress)            (/home/${USER}/data/mariadb)
```

---

## ⚙️ Service & Component Breakdown

### 1. 🌐 NGINX — Web Server & TLS Termination
- **Role**: Secure public gateway and reverse proxy.
- **Configuration**: Listens strictly on port `443`. Implements self-signed TLS certificates generated via OpenSSL on container boot.
- **Security Protocols**: Configured exclusively for `TLSv1.2` and `TLSv1.3`. HTTP (Port 80) is completely disabled.
- **Request Routing**: Forwards dynamic `.php` execution requests directly to the WordPress container via the FastCGI protocol on port `9000`.

### 2. 📰 WordPress + PHP-FPM — Application Engine
- **Role**: Dynamic web content rendering and application logic.
- **Configuration**: Runs PHP 8.2 FastCGI Process Manager listening on all interfaces (`0.0.0.0:9000`) inside the isolated network.
- **Automated Initialization**: Uses custom shell automation with `wp-cli` to download WordPress core, generate `wp-config.php`, configure database credentials from secrets, and auto-provision non-administrator user roles on first run.

### 3. 🗄️ MariaDB — Relational Database
- **Role**: Persistent data storage engine for WordPress.
- **Configuration**: Listens on port `3306` inside the private bridge network. Bound to internal container interfaces.
- **Initialization & Hardening**: Runs an automated initialization script (`mariadb-init.sh`) that sets up root privileges, creates application databases, provisions restricted database users, and deletes temporary default accounts.

---

## 💡 Engineering & Architectural Decisions

### 🐳 Custom Dockerfiles vs. Pre-Built DockerHub Images
- **Decision**: Avoided official pre-packaged images (`wordpress:latest`, `nginx:latest`, `mariadb:latest`) in favor of building custom images from `debian:bookworm`.
- **Rationale**: Building from raw Linux distributions provides total control over installed packages, minimizes security vulnerabilities (CVEs), eliminates unnecessary software bloat, and makes configuration steps explicit and audit-friendly.

### 🔒 Docker Network vs. Host Networking
- **Decision**: Implemented an explicit custom bridge network (`inception-network`).
- **Rationale**: Host networking bypasses container port isolation and exposes internal services directly to the host network interface. Using an isolated bridge network ensures MariaDB (3306) and PHP-FPM (9000) are reachable **only by designated containers** via Docker's internal DNS resolution.

### 🔑 Docker Secrets vs. Environment Variables
- **Decision**: Stored passwords in local secret files (`secrets/`) mounted at `/run/secrets/`.
- **Rationale**: Environment variables can be inspected easily via `docker inspect`, process logs, or child process environments. Docker Secrets present sensitive data as in-memory files within container filesystems, preventing credential leakage in builds or shell environments.

### 💾 Named Volumes with Host Bind Driver vs. Direct Bind Mounts
- **Decision**: Used Docker named volume drivers backed by explicit host bind paths (`/home/${USER}/data`).
- **Rationale**: Combines the management efficiency of Docker volumes with explicit host path control, ensuring persistent data survives full container teardowns (`docker compose down`) while meeting strict host location requirements.

---

## 🚀 Key Learnings & Skills Demonstrated

Through designing, implementing, and debugging this infrastructure, key competencies were mastered across DevOps, Linux system administration, and network security:

```text
├── 🛠️ DevOps & Infrastructure as Code (IaC)
│   ├── Designing multi-container topologies using Docker Compose
│   ├── Crafting optimized, multi-layer Dockerfiles with explicit entrypoints
│   ├── Orchestrating container lifecycle, health checks, and restart policies
│   └── Managing volume mounts and persistent storage lifecycles
│
├── 🛡️ Network Security & Cryptography
│   ├── Configuring TLS/SSL certificates and cipher suites (TLS 1.2 / 1.3)
│   ├── Hardening NGINX reverse proxies against unencrypted traffic
│   ├── Implementing zero-trust network segregation with Docker bridge networks
│   └── Secure credential management via Docker Secrets (/run/secrets)
│
└── 🐧 Systems Administration & Automation
    ├── Writing robust POSIX shell entrypoint scripts for container bootstrap
    ├── Automating WordPress setup and user provisioning via WP-CLI
    ├── Configuring PHP-FPM process pools (www.conf) and FastCGI communication
    └── Database administration, SQL privilege management, and health checks
```

---

## 📂 Repository Structure

```text
.
├── Makefile                        # Master orchestration commands (up, down, clean, fclean)
├── README.md                       # Comprehensive documentation & architecture guide
├── secrets/                        # Encrypted/local secrets directory (Git-ignored)
│   └── .gitkeep
└── srcs/                           # Infrastructure configuration root
    ├── .env.example                # Template for environment configuration
    ├── docker-compose.yml          # Multi-container service definitions
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile          # MariaDB Debian build instructions
        │   ├── conf/50-server.cnf  # MariaDB server configuration
        │   └── tools/mariadb-init.sh # Database boot & grant script
        ├── nginx/
        │   ├── Dockerfile          # NGINX Debian build instructions
        │   ├── conf/nginx.conf     # NGINX reverse proxy & TLS config
        │   └── tools/nginx-entrypoint.sh # SSL cert generator & boot script
        └── wordpress/
            ├── Dockerfile          # WordPress + PHP-FPM Debian build instructions
            ├── conf/www.conf       # PHP-FPM pool listener configuration
            └── tools/wp-config-create.sh # WP-CLI setup & user creation script
```

---

## 💻 Quick Start & Deployment Guide

### Prerequisites
- Operating System: **Linux** (Debian / Ubuntu recommended)
- Dependencies: **Docker Engine** (`v20.10+`), **Docker Compose plugin**, **Make**, **curl**, and **sudo** access.

### 1️⃣ Clone the Repository & Configure Environment
```bash
git clone https://github.com/souichou/inception.git
cd inception

# Create environment file from template
cp srcs/.env.example srcs/.env
```

### 2️⃣ Provision Secret Files
Create the required credential files in the `secrets/` directory (each containing its respective plaintext password):
```bash
echo "your_secure_db_password"    > secrets/db_password.txt
echo "your_secure_root_password"  > secrets/db_root_password.txt
echo "your_secure_admin_pass"     > secrets/wp_admin_password.txt
echo "your_secure_user_pass"      > secrets/wp_user_password.txt
```

### 3️⃣ Map Local Domain Name
Add the local domain mapping to your host's `/etc/hosts` file:
```bash
echo "127.0.0.1 souichou.42.fr" | sudo tee -a /etc/hosts
```

### 4️⃣ Launch Infrastructure Stack
Start the build and initialization process:
```bash
make up
```
*This command automatically prepares persistent data directories (`/home/${USER}/data`), compiles custom Docker images, and boots all containers in detached mode.*

---

## 🔍 Verification & Inspection

### Check Running Service Status
```bash
make ps
```
*All services (`mariadb`, `wordpress`, `nginx`) should report status `Up`.*

### Stream Container Logs
```bash
make logs
```

### Validate TLS 1.2 & TLS 1.3 Compliance
Test secure handshake support using `curl`:
```bash
# Test TLS v1.2 Connection
curl -v -k --tlsv1.2 https://souichou.42.fr

# Test TLS v1.3 Connection
curl -v -k --tlsv1.3 https://souichou.42.fr
```

### Verify Isolated Network Topology
```bash
docker network inspect inception-network
```
*Confirms all three containers communicate over the dedicated `inception-network` bridge.*

---

## 🧹 Stack Cleanup Commands

| Command | Action Description |
| :--- | :--- |
| `make start` | Resumes existing stopped containers without rebuilding. |
| `make stop` | Pauses running containers without destroying resources. |
| `make down` | Stops containers and removes container networks. Preserves volume data on host. |
| `make clean` | Executes `make down` and prunes unused Docker system resources & build cache. |
| `make fclean` | Full reset: stops services, deletes images, removes volumes, and wipes persistent host data (`/home/${USER}/data`). |
| `make re` | Performs a complete purge (`fclean`) and rebuilds the stack from scratch (`up`). |

---

## 👨‍💻 Author

**Souhail (souichou)**
- **GitHub**: [@souichou](https://github.com/souichou)
- **Role**: Software & Systems Engineer
