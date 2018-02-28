
# coding: utf-8

# In[1]:


# pip install pandas
import pandas as pd

from collections import Counter
from operator import itemgetter
from datetime import datetime


# In[2]:


df = pd.read_csv("shkib.csv")
df.head()


# ### Поиск 5ти пользователей, сгенерировавших наибольшее количество запросов

# In[3]:


def topRequestUser(df):
    groups = df[df["src_user"].notnull()].groupby(by=["src_user"]).groups
    user_cnt_queries = map(lambda (user, queries): (user, len(queries)), groups.items())
    topRequest = sorted(user_cnt_queries, key=itemgetter(1),reverse=True)[:5]
    return topRequest


# In[4]:

print "Top 5 users by requests:"
print topRequestUser(df)
print


# ### Поиск 5ти пользователей, отправивших наибольшее количество данных

# In[5]:


def topDataSendUser(df):
    groups = df[df["src_user"].notnull()].groupby(by=["src_user"])['output_byte']
    topDataSend = sorted(dict(groups.sum()).items(), key=itemgetter(1),reverse=True)[:5]
    return topDataSend


# In[6]:

print "Top 5 users by sent data:"
print topDataSendUser(df)
print

# ### Поиск регулярных запросов (запросов выполняющихся периодически) по полю src_user

# In[7]:


def getTop10RegularUsr(df):
    df_without_nan_user = df[df["src_user"].notnull()]
    
    columns = ['src_user', 'dest_ip', 'output_byte', 'dest_port']
    df_string = df_without_nan_user[columns].astype(str)
    cnt = Counter(map(lambda x: ' '.join(x), df_string.values))
    cnt = sorted(cnt.items(), key=itemgetter(1), reverse=True)
     
    top = cnt[:10]
    data = map(lambda (data, cnt): data.split() + [cnt], top)
    return pd.DataFrame(data=data, columns=columns + ['count_queries'], index=None)


# In[8]:

print "Top 10 regular queries by src_user:"
print getTop10RegularUsr(df)
print

# ### Поиск регулярных запросов (запросов выполняющихся периодически) по полю src_ip

# In[9]:


def getTop10RegularIP(df):
    
    columns = ['src_ip', 'dest_ip', 'output_byte', 'dest_port']
    df_string = df[columns].astype(str)
    cnt = Counter(map(lambda x: ' '.join(x), df_string.values))
    cnt = sorted(cnt.items(), key=itemgetter(1), reverse=True)
     
    top = cnt[:10]
    data = map(lambda (data, cnt): data.split() + [cnt], top)
    return pd.DataFrame(data=data, columns=columns + ['count_queries'], index=None)


# In[10]:

print "Top 10 regular queries by IP:"
print getTop10RegularIP(df)
print
