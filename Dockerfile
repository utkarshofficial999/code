FROM python:3.11-slim

WORKDIR /app

# Install git for pushing auto-solved solutions to repository
RUN apt-get update && apt-get install -y --no-install-recommends git ca-certificates && rm -rf /var/lib/apt/lists/*

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

# Default port for cloud web services (Render / Railway / Koyeb)
ENV PORT=8080
EXPOSE 8080

CMD ["python", "telegram_bot.py"]
