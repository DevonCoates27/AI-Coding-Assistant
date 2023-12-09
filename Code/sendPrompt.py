from ast import Return
import openai

print("\n\nINTERFACING WITH OPENAI\n\n")

with open("Data/APIKey.txt", 'r') as file:
  apikey = file.read()

client = openai.Client(
    api_key=apikey
    )

with open("Data/prompt.txt", 'r') as file:
    # Read the entire file
    content = file.read()

completion = client.chat.completions.create(
  model="gpt-3.5-turbo",
  messages=[
    {"role": "system", "content": content}
  ]
)

# completion2 = client.chat.completions.create(
#   model="gpt-4-0613",
#   messages=[
#     {"role": "system", "content": content}
#   ]
# )

with open("Code/JobSystemCode/CodeToTest/file1.cpp", 'w') as file:
  # Write to the file
  file.write(completion.choices[0].message.content)


# print("3.5-turbo RESPONSE: \n\n\n")
# print(completion.choices[0].message.content)
# print("\n\n\n")



print("COMPLETED")

# print("4.0 RESPONSE: \n\n\n")
# print(completion2.choices[0].message.content)
# print("\n\n")

quit()