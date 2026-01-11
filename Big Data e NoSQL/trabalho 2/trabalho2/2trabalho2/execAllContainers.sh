cd ..
docker network create -d bridge airflow-net

declare -a arr=("airflow" "celery" "minio" "streamlit" "kafka")
for i in "${arr[@]}"
do
	cd "$i"
	docker compose up build
	docker compose up -d
	cd ..
done
echo "Ambientes inicializados com sucesso."

cd 2trabalho2
if [ -z $(./mc find local/air-quality -name "airquality.csv")]; then
echo "Minio não possui bucket / arquivo. Inserindo..."
mkdir temp
cd temp
wget https://dl.min.io/client/mc/release/linux-amd64/mc
chmod +x mc

./mc alias set local http://localhost:9000 minioadmin minioadmin
./mc mb local/air-quality
./mc cp ../airquality.csv local/air-quality/

echo "Bucket e arquivo inseridos."
echo "Removendo arquivos temporários."
cd ..
rm -rf temp
else
echo "Dataframe já está no Minio."
fi
echo "Concluído inicialização e configuração do ambiente."
