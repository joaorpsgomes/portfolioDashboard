# Use the official MySQL image as the base
FROM mysql:latest

# Optionally, set environment variables
ENV MYSQL_ROOT_PASSWORD=root
ENV MYSQL_DATABASE=portfolio
ENV MYSQL_PASSWORD=root

# Expose the MySQL port
EXPOSE 3306

COPY dbFiles/portefolio_data.sql /docker-entrypoint-initdb.d/