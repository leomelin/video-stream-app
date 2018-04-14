import { makeExecutableSchema } from 'graphql-tools';

const typeDefs = [`
  type Tag {
    id: Int
    label: String
    type: String
  }
  type TagsPage {
    tags: [Tag]
    hasMore: Boolean
  }
  type Query {
    hello: String
    ping(message: String!): String
    tags(type: String!): [Tag]
    tagsPage(page: Int!, size: Int!): TagsPage
    randomTag: Tag
    lastTag: Tag
  }
  type Mutation {
    addTag(type: String!, label: String!): Tag
    startStreaming(streamKey: String!): String
  }
  schema {
    query: Query
    mutation: Mutation
  }
`];

const tags = [
  {
    id: 1,
    label: 'nothing',
    type: 'basic'
  },
  {
    id: 2,
    label: 'here',
    type: 'basic'
  },
  {
    id: 3,
    label: 'here',
    type: 'advanced'
  }
];

const resolvers = {
  Query: {
    hello(root, args, context) {
      return 'Hello world!';
    },
    ping(root, { message }, context) {
      return `Answering ${message}`;
    },
    tags(root, { type }, context) {
      return tags.filter(t => t.type === type);
    },
    lastTag(root, args, context) {
      return tags[tags.length - 1];
    }
  },
  Mutation: {
    addTag: async (root, { type, label }, context) => {
      console.log(`adding ${type} tag '${label}'`);
      const newTag = {
        id: tags[tags.length - 1].id + 1,
        label,
        type
      };
      tags.push(label);
      return newTag;
    },
    startStreaming: async (root, { streamKey }, context) => {
      console.log('should start streaming');
      return 'OK';
    }
  }
};

const jsSchema = makeExecutableSchema({
  typeDefs,
  resolvers
});

export default jsSchema;