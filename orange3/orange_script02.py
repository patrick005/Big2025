import numpy as np
import pandas as pd
from Orange.data import ContinuousVariable, DiscreteVariable, Domain, Table

X_df, y_df, m_df = in_data.to_pandas_dfs()


out_data = Table.from_pandas_dfs(X_df, y_df, m_df)
