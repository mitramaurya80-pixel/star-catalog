import pandas as pd

def clean_data(input_file, output_file):
    """
    Cleans the input CSV data by removing rows with missing 
    values and duplcates, and saves the clened data to a new csv file.
    """
    #read the input CSV file into a DataFrame
    df=pd.read_csv(input_file,comment='#',skiprows=1)  
    df_clean= df[["pl_name","disc_year","sy_dist"]].copy()  # select relevant columns
    df_clean["pl_name"]=df_clean["pl_name"].str.replace(" ","_",regex=False) # replace spaces with underscores in the "pl_name" column
    df_clean.dropna(subset=["sy_dist"], inplace=True)  # remove rows with missing values in the "sy_dist" column
    df_clean["sy_dist"] = df_clean["sy_dist"]*3.26   # convert sy_dist from parsecs to light-years
    df_clean["sy_dist"] = df_clean["sy_dist"].round(3)  # round the "sy_dist" column to 3 decimal places
    #Add a new column for exoplanet 
    df_clean["type"] = "exoplanet"

    df_clean=df_clean[["pl_name","sy_dist","type","disc_year"]]# reorder columns for clarity

    df_clean.columns=["name","distance_ly","type","discovery_year"]  # rename columns for clarity

    df_clean=df_clean.sort_values("distance_ly").head(50)  # sort the DataFrame by distance in light-years
    print(df_clean.head(10))  # print the first few rows of the cleaned DataFrame
    df_clean.to_csv(output_file, index=False)  # save the cleaned DataFrame to a new CSV file

if __name__ == "__main__":
    input_file = '../data/raw/PSCompPars_2026.07.15_04.01.20.csv'
    output_file = '../data/processed/cleaned_data.csv'
    clean_data(input_file, output_file)