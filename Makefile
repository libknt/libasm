kill:
	@pids=$$(ps aux | grep make | grep -v grep | awk '{print $$2}'); \
	if [ -n "$$pids" ]; then \
		echo "Killing make processes: $$pids"; \
		echo "$$pids" | xargs kill -9; \
	else \
		echo "No make processes found"; \
	fi