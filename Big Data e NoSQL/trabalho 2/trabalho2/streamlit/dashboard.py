import streamlit as st
import redis
import json
import time
import pandas as pd
from datetime import datetime

r = redis.Redis(
    host="redis",
    port=6379,
    db=0,
    decode_responses=True
)

st.set_page_config(
    page_title="Dashboard de Sensores",
    layout="wide"
)

st.title("📡 Dashboard de Sensores em Tempo Real")

placeholder = st.empty()

REFRESH_INTERVAL = 1  # segundos

while True:
    with placeholder.container():

        st.subheader("⏱ Dados atualizados automaticamente a cada 1 segundo")

        try:
            # Lista de sensores no Redis
            sensor_keys = r.keys("sensor:*:*")

            if not sensor_keys:
                st.warning("Nenhum dado encontrado no Redis ainda.")
                time.sleep(REFRESH_INTERVAL)
                continue

            rows = []
            for key in sensor_keys:
                raw = r.hgetall(key)
                if not raw:
                    continue
            
                sensorData = json.loads(json.dumps(raw)) #{k.decode(): v.decode() for k, v in raw.items()}
                sensorId = key.split(":", 1)[1]

                NO2 = float(sensorData.get("NO2"))
                CO = float(sensorData.get("CO"))
                rows.append({
                    "ID do Sensor": sensorId,
                    "Temperatura": float(sensorData.get("Temperature")),
                    "Umidade Relativa": float(sensorData.get("Relative_Humidity")),
                    "Umidade Absoluta": float(sensorData.get("Absolute_Humidity")),
                    "NO2": NO2,
                    "CO": CO,
                    "Status": "OK" if not NO2 > 160 and not CO > 6 else "Alerta!"
                })

            df = pd.DataFrame(rows)

            # Tabela com dados dos sensores
            st.dataframe(df, use_container_width=True)

            # Status agregado
            st.subheader("📊 Status dos Sensores")

            statusCount = df["Status"].value_counts("OK")
            st.bar_chart(statusCount)

        except Exception as e:
            st.error(f"Erro ao consultar Redis: {e}")

    time.sleep(REFRESH_INTERVAL)
